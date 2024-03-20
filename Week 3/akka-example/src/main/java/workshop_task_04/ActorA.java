package workshop_task_04;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import java.util.Random;

public class ActorA extends AbstractActor {
    ActorRef actorBRef = getContext().getSystem().actorOf(Props.create(ActorB.class));
    @Override //Always need to override
    public Receive createReceive() {  // This method is called when  message is sent
        return receiveBuilder()
                .matchEquals("start", start -> {
                    for(int i =0; i < 100; i++ ) {
                        int number = new Random().nextInt(5) + 1;
                        actorBRef.tell(number,getSelf());
                        }
                    })
                .build(); // Build is done only once.
    }
}