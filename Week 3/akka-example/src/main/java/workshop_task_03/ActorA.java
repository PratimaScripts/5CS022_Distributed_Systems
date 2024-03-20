package workshop_task_03;

import com.example.MessageA;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;

public class ActorA extends AbstractActor {

    @Override
    public Receive createReceive() {
        return receiveBuilder()
        		.match(MessageA.class, this::onMessageA)
                .build();
    }
    
    private void onMessageA(MessageA msg) {
    	ActorRef counter = getSender();
    	counter.tell(new MessageA("Message"), getSelf());
    } 
}
