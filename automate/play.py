import os
import sys
import json
import time
import pynput

path = "save/20241111224932.json"

def load_key_events():
    save_dir = os.path.join(os.path.dirname(__file__), path)
    with open(save_dir, "r") as f:
        events = json.load(f)
    return events

def replay_keys(events):
    controller = pynput.keyboard.Controller()
    prev_time = 0
    for event in events:
        time.sleep(event["time"] - prev_time)
        prev_time = event["time"]
        if event["type"] == "start":
            if len(event["key"]) == 1:
                controller.press(event["key"])
            else:
                controller.press(getattr(pynput.keyboard.Key, event["key"]))
        else:
            if len(event["key"]) == 1:
                controller.release(event["key"])
            else:
                controller.release(getattr(pynput.keyboard.Key, event["key"]))
    sys.exit()

saved_events = load_key_events()
if saved_events:
    replay_keys(saved_events)

while True:
    time.sleep(1)