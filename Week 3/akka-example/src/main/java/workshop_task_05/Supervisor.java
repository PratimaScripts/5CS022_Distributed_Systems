package workshop_task_05;

import akka.actor.AbstractActor;
import akka.actor.ActorRef;
import akka.actor.Props;

public class Supervisor extends AbstractActor{
	
	public static Props pros() {
		return Props.create(Supervisor.class, Supervisor::new);
	}
	
	private int workerCount = 10;
	private int currentWorkerIndex = 0;
	
	// Creating 10 Workers on Startup
	private ActorRef[] workers = new ActorRef[workerCount];

	@Override
	public Receive createReceive() {
		return receiveBuilder()
				.matchEquals("Start Workers", this::startWorkers)
				.match(Integer.class, this::onInteger)
				.build();
	}
	
	/*
	 * Create Worker Actors
	 * @param msg received Message
	 */
	private void startWorkers(String msg) {
		for(int i=0; i < workerCount; i++) {
			workers[i] = getContext().getSystem().actorOf(Props.create(Worker.class), "worker" + i);
		}
	}
	
	/*
	 * Sending numbers to workers
	 * @param msg Numbers
	 */
	
	private void onInteger(Integer msg) {
		workers[currentWorkerIndex].forward(msg, getContext());
		currentWorkerIndex = (currentWorkerIndex + 1) % workerCount;
	}
}
