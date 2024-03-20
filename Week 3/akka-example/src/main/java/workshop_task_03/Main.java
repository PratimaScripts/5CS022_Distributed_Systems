package workshop_task_03;

import java.io.IOException;

import com.example.MessageA;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;

public class Main {

	public static void main(String[] args) {
		ActorSystem system = ActorSystem.create();
		ActorRef counterRef = system.actorOf(Props.create(Counter.class), "counter");

        for (int i = 0; i < 20; i++) {
            ActorRef actorA = system.actorOf(Props.create(ActorA.class));
            actorA.tell(new MessageA("increment"), counterRef);
        }
		
		try {
			System.out.println("Print ENTER to end program.");
			System.in.read();
		}
		catch (IOException ignored) {}
		finally {
			system.terminate();
			System.out.println("AKKA System Terminated.");
		}

	}

}
