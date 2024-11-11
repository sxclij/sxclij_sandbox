import os
import sys
import json
import time
import pynput

def record_keys():
    print("Exit with backspace")
    listener.start()

def on_press(key):
    if str(key) == 'Key.backspace':
        listener.stop()
        save_key_events()
        sys.exit()
    elif hasattr(key, 'char'):
        key_events.append({"type": "start", "key": key.char, "time": time.time()-start_time})
    else:
        key_events.append({"type": "start", "key": str(key).split(".")[1], "time": time.time()-start_time})

def on_release(key):
    if hasattr(key, 'char'):
        key_events.append({"type": "end", "key": key.char, "time": time.time()-start_time})
    else:
        key_events.append({"type": "end", "key": str(key).split(".")[1], "time": time.time()-start_time})

def save_key_events():
    save_dir = os.path.join(os.path.dirname(__file__), "save")
    os.makedirs(save_dir, exist_ok=True)
    save_path = os.path.join(save_dir, time.strftime("%Y%m%d%H%M%S") + ".json")
    with open(save_path, "w") as f:
        json.dump(key_events, f, indent=4)


key_events = []
listener = pynput.keyboard.Listener(on_press=on_press, on_release=on_release)
start_time = time.time()
record_keys()
while True:
    time.sleep(1)