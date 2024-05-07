<?php
$servername = "localhost";
$username = "phpuser";
$password = "Password123!";
$dbname = "db12345678";

try {
    // Attempt to establish a connection to the database
    $conn = mysqli_connect($servername, $username, $password);

    // Check connection
    if (!$conn) {
        throw new Exception("Connection failed: " . mysqli_connect_error());
    }

    // Select the database
    $dbconnect = mysqli_select_db($conn, $dbname);

    if (!$dbconnect) {
        throw new Exception("Database selection failed: " . mysqli_error($conn));
    }

    // Define the SQL query
    $sqlquery = "SELECT Fullname, Address, Phone, Email FROM Contacts";

    // Execute the query
    $myresults = mysqli_query($conn, $sqlquery);

    // Check if the query executed successfully
    if (!$myresults) {
        throw new Exception("Query execution failed: " . mysqli_error($conn));
    }

    // Fetch and display results
    while ($row = mysqli_fetch_array($myresults, MYSQLI_NUM)) {
        echo($row[0]." ");
        echo($row[1]." ");
        echo($row[2]." ");
        echo($row[3]."<br>");
    }

    // Close the connection
    mysqli_close($conn);

} catch (Exception $e) {
    // Handle any exceptions that occurred
    echo "Error: " . $e->getMessage();
}
?>
