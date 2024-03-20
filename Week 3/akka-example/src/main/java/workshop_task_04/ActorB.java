package workshop_task_04;

import akka.actor.AbstractActor;
import akka.actor.ReceiveTimeout;
import scala.concurrent.duration.Duration;

public class ActorB extends AbstractActor{

    public ActorB(){
        getContext().setReceiveTimeout(Duration.create("2 seconds"));
    }
    @Override
    public Receive createReceive() {
        
        return receiveBuilder()
                .match(Integer.class, seconds -> {
                        System.out.println("Processing for " + seconds + " seconds.");
                        Thread.sleep(seconds * 1000);
                })
                .match(ReceiveTimeout.class, rt -> {
                    System.out.println("ReceiveTimeout: Stopping ActorB and creating a new instance.");
                    getContext().stop(getSelf());
                    
                })
                .build();
    }
}