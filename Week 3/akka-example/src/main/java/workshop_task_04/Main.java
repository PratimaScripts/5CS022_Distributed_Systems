package workshop_task_04;

import akka.actor.ActorRef;
import akka.actor.ActorSystem;
import akka.actor.Props;

public class Main {
    public static void main(String[] args) {
        ActorSystem system = ActorSystem.create("ActorSystem");
        ActorRef actorA = system.actorOf(Props.create(ActorA.class), "ActorA");
        actorA.tell("start", actorA);
    }
}