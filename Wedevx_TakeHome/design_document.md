Design Document for Managing Leads

1. Intro

The goal of this project is to make a lead management system to manage candidates for a hiring process. This system allows prospects to submit their info on a lead which will then notify the prospects and an internal user once the lead is submitted. Additionally, the internal user is able to change the status of a lead to "PENDING" or "REACHED OUT".

2. Tech Stack

The tech stack used in this program contain:

    FastAPI - Given python framework to use for building the API

    SQLite - Serverless database for storing lead info

    SQLAlchemy - ORM for interacting with SQLite

    Pydantic - Library to ensure correct input and output formats

    JWT - Token authentication method for one layer of security

    OAuth2 Password Flow - For user authentication to generate JWT tokens

3. System Architecture

This architecture is built around FastAPI. This application is divided into:

    FastAPI app - Main API entry point

    CRUD operations - Where database operations are handled

    Models - The format for the database values

    Authentication - Handles security to access database information

    Utils - Utility to store excess logic
    
    Tests - Where http commands can be run to test the app

4. Design choices

For how I named my variables and files, I did my best to make it short and obvious what the file or variables were used for.
For Models, the leads and the users only had necessary data except the ID. The ID is for easier navigation and retrieval in the database. I also added notes to most functions so someone can look at my code and have a general idea of what is going on.

5. Error Handling

HttpException is used for invalid requests

6. Testing

For testing, I first made the program without authentication first because I knew it would be very troublesome creating the database and making sure the authentication worked at the same time which is why there is a reference folder in case I mess up somewhere in the authentication section. After knowing all my requests worked fine and I had all the correct variables in my model, I went and added authentication to it where I tested the process in test_auth.py.

To sum it up, I tested CRUD operations then API security and lastly data validation.

7. Improvements

One improvement I can do is having a better way to add new users instead of making the user modify and run add_testuser.py and an easier way to call http requests instead of making the user modify and then run test_auth.py