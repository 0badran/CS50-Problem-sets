import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route('/')
@login_required
def index():
    """Show portfolio of stocks"""
    total = 0
    stocks_info = []
    # Get user and user's stocks.
    user = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])[0]
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM stocks WHERE user_id=? GROUP BY symbol", user["id"])
    # Setting data for the view.
    for row in rows:
        stocks_info.append({
            "symbol": row["symbol"],
            "shares": row["shares"],
            "price": lookup(row["symbol"])["price"],
            "total": lookup(row["symbol"])["price"]*row["shares"]
        })
        # Sum stocks price
        total += lookup(row["symbol"])["price"]*row["shares"]
    # Else render index page for display table of stocks.
    return render_template("index.html", companys=stocks_info, user_cash=user["cash"], stocks_total=total, usd_format=usd, len=len)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # POST
    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        shares = request.form.get("shares")
        # Check if lookup function returns data.
        if not stock:
            return apology("invalid symbol")
        # Check for a valid number.
        elif shares == "0" or not shares.isdigit():
            return apology("invalid shares")
        # Shares casting
        shares = int(request.form.get("shares"))
        total = stock["price"]*shares
        # Return user's data to check if they have enough money.
        user = db.execute("SELECT * FROM users WHERE id=?",
                          session["user_id"])[0]
        if user["cash"] < total:
            return apology("you not have enough cash")
        # Update user's cash.
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   user["cash"]-total, session["user_id"])
        # Insert buy data into a stocks table for display and update it.
        db.execute("INSERT INTO stocks (user_id, symbol, shares) VALUES (?,?,?)",
                   session["user_id"], stock["symbol"], shares)
        # Insert buy data to track transactions.
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, total, type) VALUES (?,?,?,?,?,?)",
                   session["user_id"], stock["symbol"], shares, stock["price"], total, buy.__name__)
        flash("Bought!")
        return redirect("/")
    # GET
    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    rows = db.execute(
        "SELECT * FROM transactions WHERE user_id=? ORDER BY date DESC;", session["user_id"])
    flash("Your Transactions!")
    return render_template("history.html", transactions=rows, usd_format=usd, len=len)


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get(
                "username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    # POST
    if request.method == "POST":
        symbol = request.form.get("symbol")
        stocks = lookup(symbol)
        if not stocks:
            return apology("Symbol invalid.")
        return render_template("quoted.html", company=stocks, usd_format=usd)
    # GET
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # POST
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")
        # Query to get user's.
        rows = db.execute("SELECT * FROM users WHERE username=?", username)
        #  Check if user's exists.
        if not username or len(rows) == 1:
            return apology("username is required/username already exists", 400)
        # Check password.
        if not password or password != confirm_password:
            return apology("password is required/confirm password must match", 400)
        # All are oky insert user in the database.
        user_id = db.execute("INSERT INTO users (username, hash) VALUES (?,?)",
                             username, generate_password_hash(password))
        session["user_id"] = user_id
        flash("Registered!")
        return redirect("/")
    # GET
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Group by symbol and sum shares stock as one row.
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM stocks WHERE user_id=? GROUP BY symbol", session["user_id"])
    # POST
    if request.method == "POST":
        stock = lookup(request.form.get("symbol") or "")
        shares = request.form.get("shares")
        # Check if lookup function returns data.
        if not stock:
            return apology("symbol invalid.")
        # Check for a valid number.
        elif shares == "0" or not shares.isdigit():
            return apology("number invalid.")
        # Shares casting
        shares = int(request.form.get("shares"))
        # Get the row of the stock the user has chosen to sell
        current_stock = [
            row for row in rows if row["symbol"] == stock["symbol"]][0]
        # Check if user's have enough shares.
        if current_stock["shares"] < shares:
            return apology("no enough shares")
        # Calculate the total sell
        total = shares*stock["price"]
        # Get user cash to update it.
        user = db.execute("SELECT * FROM users WHERE id=?",
                          session["user_id"])[0]
        db.execute("UPDATE users SET cash=? WHERE id=?",
                   user["cash"]+total, user["id"])
        # Get all user stocks by symbol.
        rows2 = db.execute("SELECT * FROM stocks WHERE user_id=? AND symbol=?",
                           user["id"], current_stock["symbol"])
        # Insert sell data to track transactions.
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, total, type) VALUES (?,?,?,?,?,?)",
                   session["user_id"], stock["symbol"], shares, stock["price"], total, sell.__name__)
        # A stock is not in one row in the stocks table.
        if len(rows2) > 1:
            # Delete symbol rows grouped and instead insert one row.
            db.execute("DELETE FROM stocks WHERE user_id=? AND symbol=?",
                       user["id"], current_stock["symbol"])
            db.execute("INSERT INTO stocks (symbol, shares, user_id) VALUES (?,?,?)",
                       current_stock["symbol"], current_stock["shares"]-shares, user["id"])
            # Delete a shares when sold.
            db.execute("DELETE FROM stocks WHERE shares=0;")
            flash("Sold!")
            return redirect("/")
        # Else update a stock row.
        db.execute("UPDATE stocks SET shares=? WHERE user_id=? AND symbol=?",
                   current_stock["shares"]-shares, user["id"], current_stock["symbol"])
        # Delete a shares when sold.
        db.execute("DELETE FROM stocks WHERE shares=0;")
        flash("Sold!")
        return redirect("/")
    # GET
    return render_template("sell.html", stocks=rows)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    # POST
    if request.method == "POST":
        # Get user hash.
        user = db.execute("SELECT * FROM users WHERE id = ?",
                          session["user_id"])[0]
        # Ensure password is correct.
        if not check_password_hash(user["hash"], request.form.get("current")):
            return apology("invalid password")

        # Ensure password not empty.
        elif not request.form.get("password"):
            return apology("field's required")
        # Ensure passwords is match.
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords no match")
        # Update hash.
        db.execute("UPDATE users SET hash=? WHERE id=?", generate_password_hash(
            request.form.get("password")), user["id"])
        return redirect("/")
    # GET
    return render_template("change_password.html")
