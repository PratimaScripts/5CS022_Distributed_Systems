package tutorial_task_01;

import com.example.MessageA;
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
                .match(MessageA.class, this::onMessageA)
                .match(MessageB.class, this::onMessageB)
                .build();
    }

    private void onMessageA(MessageA msg) {
        System.out.println("Actor B received Message A : "+ msg.text + " from " + getSender());
        int sen = 1+2;
        getSender().tell(new MessageB(sen), getSelf());
        System.out.println("Actor B add number. So, the result is " + sen);
    }

    private void onMessageB(MessageB msg) {
        System.out.println("Actor B received Message B : "+ msg.number + " from " + getSender());
        if(msg.number == 4) {
            getSender().tell(new MessageA("Goodbye!"), getSelf());
        }
        else {
            getSender().tell(new MessageB(4), getSelf());
        }
    }
}