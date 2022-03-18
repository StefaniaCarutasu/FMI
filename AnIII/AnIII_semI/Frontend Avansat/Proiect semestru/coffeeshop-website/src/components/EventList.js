import React from "react"

function EventList({events, handleClick}) {
    return (
        <div>
            {events.map((event, index) => (
                <React.Fragment key={event.id}>
                    <h2>{index + 1} - {event.title}</h2>
                    <p>{event.location} - {event.date}</p>
                    <button onClick={() => handleClick(event.id)}>Delete event</button>
                </React.Fragment>
            ))}
        </div>
    )
}

export default EventList
