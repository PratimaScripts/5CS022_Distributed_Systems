# code to show random quote from API, can be used in lambda function

import json
from urllib import request, parse

def lambda_handler(event, context):
    # API endpoint to fetch random quote
    url = "https://api.quotable.io/random"
    
    try:
        # Make the HTTP GET request
        response = request.urlopen(url)
        data = response.read().decode("utf-8")
        quote_data = json.loads(data)
        
        # Extract the quote and author
        quote = quote_data["content"]
        author = quote_data["author"]
        
        # Construct response
        response_message = f"{quote} - {author}"
        response_body = {
            "message": response_message
        }
        status_code = 200
        
    except Exception as e:
        # Handle any errors
        response_body = {
            "error": "Failed to fetch quote"
        }
        status_code = 500
    
    # Construct and return the response
    return {
        "statusCode": status_code,
        "headers": {
            "Content-Type": "application/json"
        },
        "body": json.dumps(response_body)
    }