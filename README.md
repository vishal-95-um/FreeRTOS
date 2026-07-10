# FreeRTOS Examples (ESP32)

This repository is a compact, hands-on collection of FreeRTOS examples targeted at learners and embedded practitioners using the ESP32 (Arduino) platform. Each numbered folder focuses on a small FreeRTOS concept with a working `.ino` sketch you can load to your board.

## Quick Start

- Prerequisites: ESP32 development board, Arduino IDE or PlatformIO.
- In Arduino IDE: Install the ESP32 board support and open the `.ino` file for a lesson.
- In PlatformIO: create a project for your ESP32 board and add the lesson `.ino` files to `src/` or use them as examples.

Build and upload from the IDE as you normally would for an ESP32 board.

## Repository Structure

- `01_tasks_intro/` — Basic task creation and scheduling (`create_tasks.ino`).
- `02_semaphores/` — Semaphore usage and interrupt-safe signaling (`semaphore_interrupt.ino`).
- `03_mutex/` — Mutex examples for protecting shared resources (`mutex.ino`).
- `04_queues/` — Message passing using queues (`queue_data_singleSensor.ino`).
- `05_event_groups/` — Event group patterns for task synchronization (`eventGroup_demoTasks.ino`).
- `06_task_notifications/` — Lightweight notifications between tasks (`distance_alert_notification.ino`).
- `07_software_timers/` — Using FreeRTOS software timers (`software_timers.ino`).

## What You'll Learn

- How to create and manage FreeRTOS tasks.
- Inter-task communication: queues, notifications, event groups.
- Synchronization primitives: semaphores and mutexes.
- Using software timers for periodic actions.

## Notes on Platforms

- Arduino IDE: Examples are written as sketches — open the `.ino` in each folder and upload to the ESP32.
- PlatformIO: Use the ESP32 platform and either copy the sketch into a `src/` main file or adapt it into a C++ project file.

## Contributing

If you'd like to add examples, open a pull request. Keep changes focused (one concept per folder) and include a short explanation of the lesson and tested board.

## License

This repository is provided for learning purposes. Add an explicit license file if you want to allow reuse.

---

Author: Vishal
