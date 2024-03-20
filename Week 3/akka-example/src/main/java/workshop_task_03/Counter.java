package workshop_task_03;

import com.example.MessageA;

import akka.actor.AbstractActor;

public class Counter extends AbstractActor {
    private int count;
    
    Counter(){
    	count = 0;
    }
    
    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(MessageA.class,this::incrementCount)
                .build();
    }

    private void incrementCount(MessageA msg) {
        count++;
        System.out.printf("Counter: Incremented count to %d\n", count);
    }
}
