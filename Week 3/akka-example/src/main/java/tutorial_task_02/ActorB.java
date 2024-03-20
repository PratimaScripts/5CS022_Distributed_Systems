package tutorial_task_02;

import com.example.MessageB;

import akka.actor.AbstractActor;
import akka.actor.Props;


public class ActorB extends AbstractActor {
 
    public static Props props() {
        return Props.create(ActorB.class, ActorB::new);
    }

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(MessageB.class, this::primeNumber)
                .build();
    }
    
   	private void primeNumber(MessageB msg) {
		System.out.println("Actor B received a number: " + msg.number + " from " + getSender());
		int start = msg.number;
		for (int num = start; num <= 10000; num++)
		{
			boolean isPrime = true;
			for (int i=2; i <= num/2; i++) {
				if(num % i == 0) {
					isPrime = false;
					break;
				}
			}
			if (isPrime == true) {
				System.out.println("Prime Numbers from Actor B: " + num);
			}
		}
		getContext().getSystem().terminate();
	}
}