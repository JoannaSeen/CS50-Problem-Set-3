import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
# Make its easier to format values as US dollars
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # return apology("TODO")
    # See how much shares the user is left
    dictionary = db.execute ("SELECT symbol, SUM(shares) FROM Transaction_History WHERE user_id = :user_id GROUP by symbol", user_id = session["user_id"])
    rows = []
    final_total = 0
    # Need to check the purchasing (history) table minus the sell(history) table to see how many stocks left for which symbol so that the sell html can select which stocks the user have left on hand to sell for the drop down option.
    for entry in dictionary:
        #If user still have shares remaining store it in this array called symbol_remaining
        #if int(row['SUM(shares)']) > 0:
        dictionary1 = lookup(entry['symbol'])
        dictionary1["sum_shares"] = int(entry['SUM(shares)'])

        dictionary1["total"] = dictionary1["sum_shares"]  * float(dictionary1["price"])
        final_total = final_total + dictionary1["total"]

        rows.append(dictionary1)

    total = float(db.execute ("SELECT cash FROM users WHERE id = :id", id = session["user_id"])[0]['cash'])

    final_total = final_total + total

    return render_template("home.html", rows=rows, total="{:.2f}".format(total), final_total = "{:.2f}".format(final_total))
    #Name
    #Current price (not the price which user bought the shares)
    #Total (total value holding for each particular company (product of shares * price +  current cash balance)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        if lookup(request.form.get("symbol")) == None:
            return apology("INVALID SYMBOL", 400)

        if int(request.form.get("shares")) <= 0:
            return apology("INVALID SHARES VALUE", 400)

        # Use lookup to determine how much is the price of the stock currently when he is buying it
        dictionary = lookup(request.form.get("symbol"))

        # Store the company Name under the variable in company
        company = dictionary ["name"]

        # Store the company symbol under the variable symbol
        symbol = dictionary["symbol"]

        # Store the current price under the variable of stock_price
        stock_price = dictionary["price"]

        # Get how much the stock the user is requesting from the buy form!
        shares = int (request.form.get("shares"))

        #SELECT how much cash the user currently has in users, recall session["user_id"] = rows[0]["id"] = id
        # Rmb that the result of db.execute comes out in form of a dictionary, it doesnt just give you the number! It will say [{'cash': 10000}] there is a key and value!
        # Two methods to go about doing this:
        # 1. By selecting and storing the column "cash" in the dictionary then extracting out the cash value inside the dictionary by dictionary["cash"]
        # 2. By selecting every column in the sql query, and storing it in dictionary then extracting out the cash value by doing row["0"]["cash"]
        row = {}
        row = db.execute ("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
        # Accessing to the cash column in the dictionary of row!
        cash = float(row[0]["cash"])
        if cash < (shares * stock_price):
            return apology ("CAN'T AFFORD", 400)

        # user is able to afford as he/she has cash >= than shares * stock_price --> go ahead and include his name in the purchase history.

        db.execute ("INSERT INTO Transaction_History (user_id, symbol, company, price, shares) VALUES (:user_id, :symbol, :company, :price, :shares)",  , symbol = symbol, company = company, price = stock_price, shares = shares)
        db.execute("UPDATE users set cash = cash - :total_spend WHERE id = :id", total_spend = (shares * stock_price), id=session["user_id"])

        return redirect("/")

    # User try to get the login form via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    dictionary = db.execute ("SELECT * FROM Transaction_History WHERE user_id = :user_id", user_id = session["user_id"])
    return render_template("history.html", rows=dictionary)


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
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User try to get the login form via GET (as by clicking a link or via redirect)
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
    if request.method =="POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        if lookup(request.form.get("symbol")) == None:
            return apology("INVALID SYMBOL", 400)

        dictionary = lookup(request.form.get("symbol"))

        return render_template("quoted.html", dictionary = dictionary)


    # User to get the quote page via GET after logging in
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Username not submitted, return apology to user
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Username not submitted, return apology to user
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username to see if there is existing username, cannot have repeated username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username not already in existing finance.db "users" table
        if len(rows) == 1:
            return apology("That username is taken. Try another", 403)

        # Password should match with that of the re-entered password
        if request.form.get("password") != request.form.get("confirmation"):
            return apology ("Those passwords didn't match. Try again.")

        # if everything else is correct then, the password given by the user should be hash and inserted into the "users" table
        username = request.form.get("username")
        hash_password = generate_password_hash(request.form.get("password"))
        db.execute ("INSERT INTO users (username, hash) VALUES (:username, :hash)", username = username, hash =hash_password)

        # Redirect user to home page
        return redirect("/")

    # User try to get the register form via GET (as by clicking a link or via redirect) --> so that we display the register page for the user
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        if int(request.form.get("shares")) <= 0:
            return apology("INVALID SHARES VALUE", 400)

        # Use lookup to determine how much is the price of the stock currently when he is selling it
        dictionary = lookup(request.form.get("symbol"))

        # Store the company Name under the variable in company
        company = dictionary ["name"]

        # Store the company symbol under the variable symbol
        symbol = dictionary["symbol"]

        # Store the current price under the variable of stock_price
        stock_price = dictionary["price"]

        # Get how much the stock the user is requesting from the buy form!

        shares = int (request.form.get("shares")) * (-1)
        print("shares = ", shares)

        shares_left = int(db.execute ("SELECT SUM(shares) FROM Transaction_History WHERE user_id = :user_id AND symbol = :symbol", user_id = session["user_id"], symbol = symbol)[0]['SUM(shares)'])

        if shares_left + shares <= 0:
            return apology("Can't Afford", 400)


        # Add user name to the transaction_history table
        rows = db.execute ("INSERT INTO Transaction_History (user_id, symbol, company, price, shares) VALUES (:user_id, :symbol, :company, :price, :shares)", user_id = session["user_id"], symbol = symbol, company = company, price = stock_price, shares = shares)
        db.execute("UPDATE users set cash = cash + :total_spend WHERE id = :id", total_spend = ((-1 * shares) * stock_price), id=session["user_id"])

        return redirect("/")

    # User try to get the register form via GET (as by clicking a link or via redirect) --> give the user the sell page
    else:
        # See how much shares the user is left

        dictionary = db.execute ("SELECT symbol, SUM(shares) FROM Transaction_History WHERE user_id = :user_id GROUP by symbol", user_id = session["user_id"])

        # Need to check the purchasing (history) table minus the sell(history) table to see how many stocks left for which symbol so that the sell html can select which stocks the user have left on hand to sell for the drop down option.
        symbols_remaining = []
        for row in dictionary:
            #If user still have shares remaining store it in this array called symbol_remaining
            if int(row['SUM(shares)']) >= 1:
                symbols_remaining.append(row["symbol"])

        return render_template("sell.html", symbols_remaining = symbols_remaining)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
