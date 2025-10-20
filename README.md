# San Andreas GP

A racing and freemode gamemode for SA-MP (San Andreas Multiplayer).

[![sampctl](https://img.shields.io/badge/sampctl-san--andreas--gp-2f2f2f.svg?style=for-the-badge)](https://github.com/msh31/san-andreas-gp)

## Information
This gamemode was inspired by Need For Speed Unbound & Heat's multiplayer. \
(Like NFS, the player is always inside a vehicle in 99% of cases)

## Features (wip)
- Freeroam with joinable races through invites or map markers
- Car shop and garages for players to use.
- Level system, like NFS Heat. (Daytime: earn money, Nightime: earn REP/XP)
- Authentication system
- Race statistics tracking (wins/losses & more!)

### Race types
- Drifting, with GTA Online like gameplay
- Drag races
- Sprint races
- Circuit races
- Off road races
- Motorcycle races

## Development

### Prerequisites

- [sampctl](https://github.com/Southclaws/sampctl) - SA-MP development tool
- MySQL server (local or remote)

### Setup

1. Clone the repository:
```bash
git clone https://github.com/msh31/san-andreas-gp.git
cd san-andreas-gp
```

2. Install dependencies:
```bash
sampctl p ensure
```

3. Set up your MySQL database:
   - Create a database named `sagp`
   - Update connection details in `sagp.pwn` if needed
   - Import the provided database schema *(to create)*

4. Build the gamemode:
```bash
sampctl p build
```

5. Run the server:
```bash
sampctl p run
```

### Building

**Windows:**
```bash
sampctl p build
```

**macOS/Linux:**
```bash
sampctl build
```

## Contributing

Pull requests are welcome! For major changes, please open an issue first.

## License
To be decided.
