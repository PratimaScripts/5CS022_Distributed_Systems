// Import required Firebase services
import { initializeApp } from
    "https://www.gstatic.com/firebasejs/9.18.0/firebase-app.js";
import {
    Firestore,
    getFirestore,
    onSnapshot,
    query,
    collection,
    orderBy,
    addDoc, doc, setDoc, deleteDoc
} from 'https://www.gstatic.com/firebasejs/9.18.0/firebase-firestore.js';

// Your web app's Firebase configuration
const firebaseConfig = {
    apiKey: "use your own",
    authDomain: " use your own ",
    projectId: "use your own",
    storageBucket: "use your own",
    messagingSenderId: "use your own",
    appId: "use your own"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getFirestore(app);

// Get a live data snapshot (i.e. auto-refresh) of our Reviews collection
const q = query(collection(db, "Reviews"), orderBy("book_name"));
const unsubscribe = onSnapshot(q, (snapshot) => {
    // Empty HTML table
    $('#reviewList').empty();
    // Loop through snapshot data and add to HTML table
    var tableRows = '';
    snapshot.forEach((doc) => {
        tableRows += '<tr>';
        tableRows += '<td>' + doc.data().book_name + '</td>';
        tableRows += '<td>' + doc.data().book_rating + '/5</td>';
        tableRows += '<td><button class="updateBtn" data-id="' + doc.id + '">Update</button><button class="deleteBtn" data-id="' + doc.id + '">Delete</button></td>';
        tableRows += '</tr>';
    });
    $('#reviewList').append(tableRows);
    // Display review count
    $('#mainTitle').html(snapshot.size + " book reviews in the list");

    $('.updateBtn').css({
        'background-color': '#28a745',
        'color': '#fff',
        'border': 'none',
        'padding': '5px 10px',
        'cursor': 'pointer',
        'border-radius': '4px',
        'margin-right': '5px'
    });

    $('.deleteBtn').css({
        'background-color': '#dc3545',
        'color': '#fff',
        'border': 'none',
        'padding': '5px 10px',
        'cursor': 'pointer',
        'border-radius': '4px'
    });
});

// Add button pressed
$("#addButton").click(function () {

    // Add review to Firestore collection
    const docRef = addDoc(collection(db, "Reviews"), {
        book_name: $("#bookName").val(),
        book_rating: parseInt($("#bookRating").val())
    });
    // Reset form
    $("#bookName").val('');
    $("#bookRating").val('1');
});


// Update button pressed
$('#reviewList').on('click', '.updateBtn', function () {
    const docId = $(this).data('id');
    const newName = prompt("Enter new book name:");
    const newRating = parseInt(prompt("Enter new book rating:"));
    if (newName && !isNaN(newRating)) {
        setDoc(doc(db, "Reviews", docId), {
            book_name: newName,
            book_rating: newRating
        }, { merge: true })
            .then(() => {
                console.log("Document successfully updated!");
            })
            .catch((error) => {
                console.error("Error updating document: ", error);
            });
    }
});

// Delete button pressed
$('#reviewList').on('click', '.deleteBtn', function () {
    const docId = $(this).data('id');
    if (confirm("Are you sure you want to delete this review?")) {
        deleteDoc(doc(db, "Reviews", docId))
            .then(() => {
                console.log("Document successfully deleted!");
            })
            .catch((error) => {
                console.error("Error deleting document: ", error);
            });
    }
});