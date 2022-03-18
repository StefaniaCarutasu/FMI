/* eslint-disable jsx-a11y/anchor-is-valid */
/* eslint-disable no-unused-vars */
import logo from './logo.svg';
import './App.css';
import {useState} from 'react';
import Title from './components/Title';
import Modal from './components/Modal';
import EventList from './components/EventList';
import NewEventForm from './components/NewEventForm';

function App() {
  const [showModal, setShowModal] = useState(false);
  const [showEvents, setShowEvents] = useState(true);
  const [events, setEvents] = useState([]);

  const addEvent = (event) => {
    setEvents((prevEvents) => {
      return [...prevEvents, event]
    } )

    setShowModal(false);
  }
  
  const handleClick = (id) => {
    setEvents((prevEvents) => {
      return prevEvents.filter((event) => {
        return id !== event.id;
      })
    })
    
  }
  console.log(showModal);
  const handleClose = () => {
    setShowModal(!showModal);
  }
  return (
    <div className="App">
      <Title />
     
      {showEvents && (<div>
        <button onClick={() => setShowEvents(false)}>Hide events</button>
        </div>)}
      {!showEvents && (<div>
        <button onClick={() => setShowEvents(true)}>Show events</button>
      </div>)}
      
      {showEvents && <EventList events = {events} handleClick={handleClick} />}

     
      {showModal && <Modal handleClose = {handleClose}>
        <NewEventForm addEvent = {addEvent} />
      </Modal>
      }

      {!showModal && 
       <button onClick={handleClose}>Add New Event</button>
      }
      
    </div>
  );
}

export default App;
