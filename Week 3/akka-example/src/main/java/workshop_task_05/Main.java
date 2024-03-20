package workshop_task_05;

import java.io.IOException;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;

public class Main {
	public static void main(String[] args) {
        ActorSystem system = ActorSystem.create("PrimeNumberSystem");
        ActorRef producer = system.actorOf(Props.create(Producer.class), "producer");
        producer.tell("Start", ActorRef.noSender());
        
        try {
            System.out.println("Press ENTER twice to end program.");
            System.in.read();
        }
        catch (IOException ignored) { }
        finally {
            system.terminate();
            System.out.println("Terminated.");
        }
    }
}
