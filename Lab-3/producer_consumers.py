import threading
import time

'''
This program simulates a producer-consumer problem using threads. The producer-consumer problem is a 
classic synchronization problem where there are two types of threads: producers and consumers. Producers produce 
data and put it into a shared buffer, while consumers consume data from the buffer. The problem is to make sure 
that the producers and consumers do not interfere with each other and that the consumers do not consume data that has not been produced yet.
'''


class SharedBuffer:
    def __init__(self, size, producers=4, consumers=10):
        # Internal shared buffer
        self.buffer = []
        # Mutex to protect the buffer
        self.mutex = threading.Lock()
        # Semaphores to signal when the buffer is not empty
        self.notEmpty = threading.Semaphore(0)
        # Semaphores to signal when the buffer is not full
        self.notFull = threading.Semaphore(size)
        # Flag to signal that production is done
        self.doneProducing = False
        # keep track of the number of producers
        self.producers = producers
        # keep track of the number of consumers
        self.consumers = consumers

    '''
    Add a message to the buffer. If the buffer is full, the producer will wait.
    '''

    def add_message(self, message):
        # TODO: wait if buffer is full
        self.notFull.acquire() # will decrement the semaphore value by 1 if buffer is not full or wait until it is not full
        # not Full contains the amount of available space in the buffer

        with self.mutex:
            self.buffer.append(message)
        # TODO: signal that buffer is not empty
        self.notEmpty.release() # will increment the semaphore value by 1 and signal that buffer has a new message
        # not empty contains the amount of messages in the buffer

    '''
    Read a message from the buffer. If the buffer is empty, the consumer will wait.
    '''

    def read_message(self):
        message = None
        # TODO: wait if buffer is empty
        self.notEmpty.acquire() # not empty contains the amount of messages in the buffer


        with self.mutex:
            # TODO: if production is done and buffer is empty, return None (check the buffer length)
            if len(self.buffer) == 0:
                # TODO: release the requried semaphore to avoid deadlock
                self.notEmpty.release() # in case more consumers need to exit
                # Return None if production is done and buffer is empty
                return None

            message = self.buffer.pop(0) # reads the first message in the buffer
        # TODO: signal that buffer is not full
        self.notFull.release() # increments available space in the buffer by 1

        return message # Return the message at the front of the buffer

    '''
    Mark that production is done. This will be used by the producers to signal that they are done producing.
    '''

    def mark_done_producing(self):
        with self.mutex:
            # TODO: set the flag to signal that production is done
            self.doneProducing = True

            # Release semaphore to ensure all consumers can exit
            # TODO: release the semaphore for each consumer (you may need to release it multiple times)
            for i in range(self.consumers):
                self.notEmpty.release() # will increment the semaphore value by 1 in case any consumer is busy waiting for a message 

            #pass  # Remove this line when you implement the method

    def check_done_producing(self):
        with self.mutex:
            return self.doneProducing and len(self.buffer) == 0


# Shared buffer
buffer = None

'''
Producer and consumer functions. Each producer produces multiple messages and each consumer consumes messages until production is done.
'''


def producer(thread_id, write_time=2):
    # Each producer produces 5 messages
    for message_number in range(5):
        message = f"Message {message_number} from Producer {thread_id}"
        buffer.add_message(message)
        print(f"Producer {thread_id} produced: {message}")
        time.sleep(write_time)  # Simulate writing time (e.g., network delay, disk I/O, etc.
    # After the last producer finishes, signal that production is done. Note that 4 is the number of producers
    if thread_id == 4 - 1:
        buffer.mark_done_producing()


'''
Consumer function. Each consumer consumes messages until production is done and the buffer is empty.
'''


def consumer(thread_id, read_time=1):
    while True:
        # TODO: consume a message from the buffer
        message = buffer.read_message()
        if message is None:
            # TODO: break the loop if production is done and buffer is empty
            if buffer.check_done_producing():
                break
            #pass  # Remove this line when you implement the method
        print(f"Consumer {thread_id} consumed: {message}")
        time.sleep(read_time)  # Simulate reading time


def main(producer_num=5, consumer_num=10, buffer_size=1, read_time=2, write_time=3):
    global buffer
    # Initialize shared buffer
    buffer = SharedBuffer(buffer_size, producer_num, consumer_num)

    producers = [threading.Thread(target=producer, args=(i, write_time))
                 for i in range(producer_num)]
    consumers = [threading.Thread(target=consumer, args=(i, read_time))
                 for i in range(consumer_num)]

    start_time = time.time()  # Record start time

    for p in producers:
        p.start()

    for c in consumers:
        c.start()

    for p in producers:
        p.join()

    for c in consumers:
        c.join()

    end_time = time.time()  # Record end time


    print("All producers and consumers have finished.")
    print(f"Total execution time: {format(end_time - start_time, '.2f')} seconds")

if __name__ == '__main__':
    main()
