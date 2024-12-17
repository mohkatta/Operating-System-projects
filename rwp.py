import threading
import time
import random

class SharedResource:
    def __init__(self):
        self.readers_count = 0
        self.mutex = threading.Lock()
        self.write_lock = threading.Semaphore(1)  # Only one writer at a time
        self.read_lock = threading.Semaphore(1)   # Control access for readers

    def read(self, reader_id):
        with self.mutex:
            if self.readers_count == 0:
                self.write_lock.acquire()  # First reader blocks writers
            self.readers_count += 1
        
        print(f"Reader {reader_id} is reading.")
        time.sleep(random.uniform(0.1, 0.5))  # Simulate reading time

        with self.mutex:
            self.readers_count -= 1
            if self.readers_count == 0:
                self.write_lock.release()  # Last reader releases the lock

    def write(self, writer_id):
        self.write_lock.acquire()  # Wait until it's safe to write
        print(f"Writer {writer_id} is writing.")
        time.sleep(random.uniform(0.1, 0.5))  # Simulate writing time
        self.write_lock.release()

class ReaderThread(threading.Thread):
    def __init__(self, reader_id, shared_resource):
        threading.Thread.__init__(self)
        self.reader_id = reader_id
        self.shared_resource = shared_resource

    def run(self):
        while True:
            self.shared_resource.read(self.reader_id)
            time.sleep(random.uniform(0.1, 0.5))

class WriterThread(threading.Thread):
    def __init__(self, writer_id, shared_resource):
        threading.Thread.__init__(self)
        self.writer_id = writer_id
        self.shared_resource = shared_resource

    def run(self):
        while True:
            self.shared_resource.write(self.writer_id)
            time.sleep(random.uniform(0.1, 0.5))

def main():
    shared_resource = SharedResource()
    readers = [ReaderThread(i, shared_resource) for i in range(5)]
    writers = [WriterThread(i, shared_resource) for i in range(3)]

    for reader in readers:
        reader.start()
    for writer in writers:
        writer.start()

if __name__ == "__main__":
    main()


