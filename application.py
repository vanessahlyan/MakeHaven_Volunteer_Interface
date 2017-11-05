from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, shares, SUM(shares), user_id FROM transactions WHERE user_id = :u GROUP BY symbol", u=session["user_id"])

    # initialize a list of dictionaries containing each stock's information
    stocks_total = 0
    for stock in stocks:
        stock_current = lookup(stock['symbol'])
        stock["current_price"] = stock_current["price"]
        stocks_total += stock_current["price"] * stock["SUM(shares)"]
        stock["value"] = usd(stock_current["price"] * stock["SUM(shares)"])
    # access cash from users table
    cash = db.execute("SELECT cash FROM users WHERE user_id = :s", s=session["user_id"])

    # if there are no stock holdings, just output cash amount as grand_total
    if not stocks:
        return render_template("index.html", stocks=stocks, grand_total=usd(cash[0]["cash"]))
    else:
        grand_total = stocks_total + cash[0]["cash"]
        return render_template("index.html", stocks=stocks, grand_total=usd(grand_total), cash=usd(cash[0]["cash"]))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    elif request.method == "POST":
        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        else:
            # Check if symbol exists
            quote = lookup(request.form.get("symbol"))
            if not quote:
                return apology("symbol does not exist")

            # Ensure "shares" was submitted
            if not request.form.get("shares"):
                return apology("must provide shares")
            else:
                # Check if shares is positive integer
                try:
                    shares = int(request.form.get("shares"))
                except ValueError:
                    return apology("Shares must be integer.")
                if shares <= 0:
                    return apology("Shares must be positive .")

            # SELECT how much cash the user currently has in users
            available_cash = db.execute(
                "SELECT cash FROM users WHERE user_id = :s", s=session["user_id"])
            if available_cash[0]["cash"] < shares * quote["price"]:
                return apology("You do not have enough cash to purchase this stock.")
            else:
                # add stock into transactions
                db.execute("INSERT INTO transactions(user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :time)",
                           user_id=session["user_id"], symbol=request.form.get("symbol"), shares=shares, price=quote["price"], time=datetime.now())
                # update cash
                cash = available_cash[0]["cash"] - shares * quote['price']
                db.execute("UPDATE users SET cash = :c  WHERE user_id = :s",
                           c=cash, s=session["user_id"])
                return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # retrieve information from transactions database
    transactions = db.execute(
        "SELECT symbol, shares, price, time FROM transactions WHERE user_id = :u", u=session["user_id"])
    for transaction in transactions:
        if transaction["shares"] < 0:
            transaction["nature"] = "sale"
        elif transaction["shares"] > 0:
            transaction["nature"] = "purchase"
        else:
            return apology("The nature of your transaction cannot be determined.")
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["user_id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        # Ensure symbol is submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol")
        # Ensure symbol is valid
        quote = lookup(request.form.get("symbol"))
        if not quote:
            return apology("Stock quote is invalid")
        return render_template("quoted.html", name=quote["name"], price=usd(quote["price"]), symbol=quote["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    elif request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")
        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must confirm password")
        # Ensure password and confirmation match
        elif (request.form.get("password") != request.form.get("confirmation")):
            return apology("password and confirmation must match")
        # if all inputs are valid, hash user's password
        else:
            hash = generate_password_hash(request.form.get("password"))
            # add username and hash number into database
            result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                                username=request.form.get("username"), hash=hash)
            if not result:
                return apology("username already exists")
        rows = db.execute("SELECT user_id FROM users")
        session["user_id"] = rows[0]["user_id"]
        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    stocks = db.execute(
        "SELECT symbol FROM transactions WHERE user_id = :u GROUP BY symbol", u=session["user_id"])
    if request.method == "GET":
        return render_template("sell.html", stocks=stocks)
    elif request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must select a stock that you own")
        elif not request.form.get("shares"):
            return apology("must input number of shares")
        elif int(request.form.get("shares")) <= 0:
            return apology("number of shares must be positive integer")
        else:
            # select shares of desired symbol
            shares = db.execute("SELECT shares FROM transactions WHERE user_id = :u AND symbol = :s",
                                u=session["user_id"], s=request.form.get("symbol"))
            # check if there are enough shares to sell
            if int(request.form.get("shares")) > shares[0]["shares"]:
                return apology("You don't have that many shares to sell.")
            else:
                # check current price of stock
                stock_current = lookup(request.form.get("symbol"))
                sale_value = stock_current["price"] * int(request.form.get("shares"))
                # insert sale record at current price into transactions
                db.execute("INSERT INTO transactions (user_id, symbol, shares, price, time) VALUES(:user_id, :symbol, :shares, :price, :time)",
                           user_id=session["user_id"], symbol=request.form.get("symbol"), shares=-int(request.form.get("shares")), price=stock_current["price"], time=datetime.now())
                # add to cash
                db.execute("UPDATE users SET cash = cash + :s WHERE user_id = :u",
                           s=sale_value, u=session["user_id"])
                # return apology if after number of shares = 0 after decrement
                shares_remaining = shares[0]["shares"]
                if shares_remaining == 0:
                    db.execute("DELETE FROM transactions WHERE user_id = :u AND symbol = :s",
                               u=session["user_id"], s=stock["symbol"])
                    return apology("You have no more of this stock left.")
                else:
                    return(redirect("/"))


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    if request.method == "GET":
        return render_template("change_password.html")
    elif request.method == "POST":
        if not request.form.get("username"):
            return apology("You must provide username.")
        elif not request.form.get("password"):
            return apology("You must provide your password.")
        else:
            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username",
                              username=request.form.get("username"))

            # Ensure username exists and password is correct
            if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
                return apology("invalid username and/or password, you are not authorized to change password", 403)
            else:
                if not request.form.get("new_password"):
                    return apology("You must provide a new password.", 403)
                elif not request.form.get("confirmation"):
                    return apology("You must provide a password confirmation.", 403)
                elif request.form.get("new_password") != request.form.get("confirmation"):
                    return apology("Your new password and confirmation must match", 403)
                else:
                    hash = generate_password_hash(request.form.get("new_password"))
                    db.execute("UPDATE users SET hash = :h  WHERE user_id = :s",
                               h=hash, s=session["user_id"])
                    return(redirect("/logout"))


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
