package tutorial_task_02;

import java.io.IOException;

import com.example.MessageB;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;

public class Main {

	public static void main(String[] args) {
		
		ActorSystem system = ActorSystem.create();
		
		ActorRef actorARef = system.actorOf(Props.create(ActorA.class));
        ActorRef actorBRef = system.actorOf(Props.create(ActorB.class));
        
        actorARef.tell(new MessageB(5000),actorARef);
        actorBRef.tell(new MessageB(5001),actorBRef);

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