import firebase from "firebase/app";
import "firebase/firestore";

const firebaseConfig = {
    apiKey: "AIzaSyAaBGkgI0pSvAxCspksBdgJhbdpbspGsgw",
    authDomain: "cooking-ninja-site-52c03.firebaseapp.com",
    projectId: "cooking-ninja-site-52c03",
    storageBucket: "cooking-ninja-site-52c03.appspot.com",
    messagingSenderId: "622371056431",
    appId: "1:622371056431:web:ad3fd9168f3570afc10fda"
  };


  // init firebase
  firebase.initializeApp(firebaseConfig)

  // init services
  const projectFirestore = firebase.firestore()

  export { projectFirestore }