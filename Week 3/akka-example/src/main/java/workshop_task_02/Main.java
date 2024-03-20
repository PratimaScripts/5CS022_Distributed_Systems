package workshop_task_02;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;
import java.io.IOException;

class Main {

    public static void main(String[] args) {

        ActorSystem system = ActorSystem.create();
        ActorRef actorARef = system.actorOf(Props.create(ActorA.class));
        
        //Primitive Data Types
        actorARef.tell(4, actorARef);
        actorARef.tell(44.0, actorARef);
        actorARef.tell(55.4f, actorARef);
        actorARef.tell(false, actorARef);
        actorARef.tell(456L, actorARef);
        actorARef.tell('A', actorARef);
        actorARef.tell((byte) 1, actorARef);
        actorARef.tell((short) 2, actorARef);
 
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