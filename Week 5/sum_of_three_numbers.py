import json

print('Loading function')


def lambda_handler(event, context):
    #print("Received event: " + json.dumps(event, indent=2)
    value1 = int(event['key1'])
    value2 = int(event['key2'])
    value3 = int(event['key3'])
    
    result = value1 + value2 + value3
    
    return f"The final result is: {result}"
    #raise Exception('Something went wrong')
