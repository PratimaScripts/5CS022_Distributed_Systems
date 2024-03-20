package workshop_task_05;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;
import akka.event.Logging;
import akka.event.LoggingAdapter;

import java.util.Random;

public class Producer extends AbstractActor {

    private final LoggingAdapter log = Logging.getLogger(getContext().getSystem(), this);
    private int primeCount = 0;
    private final int totalNumbers = 1000;
    private final ActorRef supervisorRef;

    public Producer() {
        supervisorRef = getContext().getSystem().actorOf(Props.create(Supervisor.class), "supervisor");
    }

    public static Props props() {
        return Props.create(Producer.class, Producer::new);
    }

    @Override
    public Receive createReceive() {
        return receiveBuilder()
                .match(String.class, this::onString)
                .build();
    }

    private void onString(String msg) {
        log.info("Received message: {}", msg);
        if (msg.startsWith("The number")) {
            primeCount++;
            log.info(msg);
            if (primeCount >= totalNumbers) {
                log.info("All numbers checked. Terminating Actor System.");
                getContext().getSystem().terminate();
            }
        }
    }

    @Override
    public void preStart() {
        Random r = new Random();
        int low = 10000;
        int high = 100000;
        supervisorRef.tell(new String("Start Workers"), getSelf());
        // Sending Numbers
        for (int i = 0; i < 1000; i++) {
            supervisorRef.tell(Integer.valueOf(r.nextInt(high - low) + low), getSelf());
        }
    }
}