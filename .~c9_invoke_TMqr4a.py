from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required
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

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")


@app.route("/")
@login_required
def index():
    """Show everyone's username, credit, tasks, task description"""
    users = db.execute(
        "SELECT username, credit FROM users WHERE user_id = :u", u=session["user_id"])
    tasks = db.execute("SELECT task FROM tasks WHERE user_id = :u", u = session["user_id"])

    return render_template("index.html", users=users)


@app.route("/signup", methods=["GET", "POST"])
@login_required
def signup():
    """Add task for user"""
    if request.method == "GET":
        return render_template("signup.html")

    elif request.method == "POST":
        # Add task to table 'tasks'
        db.execute("INSERT INTO tasks (user_id, task) VALUES (:user_id, :task)",
                   user_id=session["user_id"], task=request.form.get("task"))

        # Redirect user to home page
        flash("Signed up!")
        return redirect("/")


@app.route("/checkin", methods=["GET", "POST"])
@login_required
def checkin():
    """Add credit for user"""
    if request.method == "GET":
        return render_template("checkin.html")

    elif request.method == "POST":
        # Check if user signed up for the task
        owned_task = db.execute("SELECT task FROM tasks WHERE user_id = :user_id",
                                  user_id=session["user_id"], task=request.form.get("task"))
        if not owned_task:
            return apology("Did not sign up for the task", 400)

        # Update credit
        old_credit = db.execute("SELECT credit FROM users WHERE id = :id", id=session["user_id"])
        new_credit = old_credit[0]["credit"] + 1
        db.execute("UPDATE users SET credit = :new_credit WHERE id = :id",
                   new_credit=new_credit, id=session["user_id"])

        # Redirect user to home page
        flash("Checked in!")
        return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

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
        
        
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")
def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
