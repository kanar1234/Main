import requests

lead_data = {
    "first_name": "John",
    "last_name": "Doe",
    "email": "john.doe5@example.com",
    "resume": "Test text."
}

# Make a POST request to the FastAPI server to create a new lead
# response = requests.post("http://127.0.0.1:8000/leads/", json=lead_data)

# Make a GET request to the FastAPI server to get leads
response = requests.get("http://127.0.0.1:8000/leads/")

# Define the lead ID and the state to update
lead_id = 5  # ID of the lead you want to update
state = "REACHED_OUT"  # The state to update

# Make a PUT request to the FastAPI server to update the lead with state as query parameter
# response = requests.put(f"http://127.0.0.1:8000/leads/{lead_id}?state={state}")

# Check if the request was successful (status code 200)
if response.status_code == 200:
    updated_lead = response.json()  # Convert the response to JSON
    print(f"Response successful: {updated_lead}")
else:
    print(f"Failed to update lead. Status code: {response.status_code}")
    # print(response.json())  # Print response error for debugging
