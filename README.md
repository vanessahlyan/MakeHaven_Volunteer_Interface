(Note: the program requires the module "dateutil", thus any CS50 IDE server needs to download python-dateutil package by executing the following two commands: "sudo apt-get install python-pip"; "sudo pip install python-dateutil".)

Our project is a volunteer community interface for a local service organization called MakeHaven. We aim to enhance motivation, communication, and organization for volunteer work through various functionalities. The project is stored in CS50 IDE and is compiled through Flask.

**

FOR USERS:

To browse the website, a volunteer would need to register an account on the website. The user's account information would be stored in the table "users" in our database "project.db."

After registering or logging in to their accounts, users are brought to the index page. Users may scroll through the carousel on the index page to view photos of MakeHaven volunteering, an upcoming task that the user already signed up for, and an inspirational quote.

To view more information about the tasks that they have signed up for, users should click the "User Info" tab on the top-left navigation bar of the website and will be redirected to the "User Info" page. This page displays a user's name, username, and volunteer credit. Users may change their username or password by clicking on the "Change Username" or Change Password" links. Furthermore, there is a table displaying information about each task a user has signed up for, and users can add the event to their own Google/iCloud/Outlook/ Yahoo calendar by clicking on the corresponding tab on the right of each task. If users would like to access their Slack account to set up a reminder for themselves, they may also click on the link provided above the table to be redirected to the sign-in page for Slack.

To view all the volunteer tasks that are going on at MakeHaven, user should click on the "All Tasks" tab on the top-left navigation bar. Users are encouraged to watch the introductory video to MakeHaven before they sign up for any tasks. To sign up for a task, users just need to click on the button corresponding to each task. Their sign-up-time and other information will be recorded in the database.

When it comes time to do the task, users should click on the "Check In" tab on the top-left navigation bar. The "Check In" page displays tasks that the user have signed up for, and at the bottom of the page there is a drop-down menu for users to check in for a task. Once a user checks in, a corresponding amount of credit for the task will be added to the user's account information in the "users" database.
To view one's credit score compared to other volunteers', users can click on the "Rankings" tab on the op-left navigation bar. The "Rankings" page displays the ranking and credit score for each volunteer.

Finally, users may access a discussion forum through the "Message Board" tab on the top-left navigation bar. Users may view any notifications posted by administrative staff. Users may also post messages in the forum and adjust the size of the text box if necessary. After submission, users' comments need to be approved by administrative staff and their "approved" status changed to 0 in the "forum" table. Once the status is changed, the comment will appear on the message board.

**

FOR ADMINS:

Admins have the added functionalities of: 1) Add Tasks; 2) Remove Tasks; 3) Approve or delete user comments; 4) Post Admin notification (at Message Board).

To add tasks, go to "Add Tasks." All fields are mandatory except for the recurrence cycle. If a task does not recur regularly, simply leave the field blank. The rest of the functions are straightforward to navigate.
