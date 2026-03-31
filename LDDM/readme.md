# Flutter Class Assignments

This repository contains a collection of Flutter projects developed for my class
assignments. Each directory represents a specific exercise.

## Structure

Each assignment is contained within its own Flutter project folder, following
the naming convention: `XX_assignment_name`.

- **`(01_login_screen/)[./01_login_screen]`**: Assignment 1.
- **`(02_crud_screen/)[./02_crud_screen]`**: Assignment 2.

---

## How to Run

To run any of the assignments locally, follow these steps:

### 1. Prerequisites

Ensure you have the Flutter SDK installed and configured.

- Check your setup by running: `flutter doctor`

### 2. Navigate to the Project

Open your terminal and enter the specific assignment directory:

```bash
cd xx_assignment_name
```

### 3. Install Dependencies

Fetch the required packages listed in the `pubspec.yaml`:

```bash
flutter pub get
```

### 4. Run the App

Launch the application on your connected device or emulator:

```bash
flutter run
```

---

## Development

### Using Nix

This repo includes a `flake.nix`, so you can enter a reproducible development
environment with all dependencies pre-installed by running:

```bash
nix develop
```

### Creating a New Assignment

When starting a new task, use the following command from the root directory to
maintain the naming convention:

```bash
flutter create 03_new_assignment_name
```

---

## Notes

- **Assets:** Most projects use custom fonts or images located in the `assets/`
  folder of their respective directories.
- **Lib Folder:** The core logic and UI code reside in `lib/main.dart`.
