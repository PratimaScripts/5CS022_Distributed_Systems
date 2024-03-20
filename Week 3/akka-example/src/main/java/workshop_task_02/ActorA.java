package workshop_task_02;

import akka.actor.AbstractActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class ActorA extends AbstractActor {

    LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);

    @Override
    public Receive createReceive() {
        return receiveBuilder()
        		.matchAny(msg -> log.info("Actor A received message: {}", msg))
                .build();
    }
}