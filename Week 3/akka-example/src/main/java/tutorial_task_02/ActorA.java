package tutorial_task_02;

import com.example.MessageB;

import akka.actor.AbstractActor;
import akka.event.Logging;
import akka.event.LoggingAdapter;

public class ActorA extends AbstractActor {
    LoggingAdapter log = Logging.getLogger(getContext().system(), this);

    @Override
    public Receive createReceive() {
        return receiveBuilder()
        		.match(MessageB.class, this::primeNumber)
                .build();
    }
    
    private void primeNumber(MessageB msg) {
        System.out.println("Actor A received a number: " + msg.number + " from " + getSender());
        int endpoint = msg.number;
        for (int num = 2; num <= endpoint; num++) {
            boolean isPrime = true;
            for (int i = 2; i <= num / 2; i++) {
                if (num % i == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                System.out.println("Prime Numbers from Actor A: " + num);
            }
        }
        getContext().getSystem().terminate();
    }
}