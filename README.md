<div align="center">

```
███████╗ ██████╗     ██╗      ██████╗ ███╗   ██╗ ██████╗ 
██╔════╝██╔═══██╗    ██║     ██╔═══██╗████╗  ██║██╔════╝ 
███████╗██║   ██║    ██║     ██║   ██║██╔██╗ ██║██║  ███╗
╚════██║██║   ██║    ██║     ██║   ██║██║╚██╗██║██║   ██║
███████║╚██████╔╝    ███████╗╚██████╔╝██║ ╚████║╚██████╔╝
╚══════╝ ╚═════╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝ 
```

**A 2D tile-based game engine built from scratch in C**

[![Language](https://img.shields.io/badge/language-C-blue.svg?style=flat-square)](https://en.wikipedia.org/wiki/C_(programming_language))
[![MiniLibX](https://img.shields.io/badge/graphics-MiniLibX-orange.svg?style=flat-square)](https://harm-smits.github.io/42docs/libs/minilibx)
[![School](https://img.shields.io/badge/school-42-black.svg?style=flat-square)](https://42.fr)
[![Norm](https://img.shields.io/badge/norminette-passing-brightgreen.svg?style=flat-square)](https://github.com/42School/norminette)

</div>

---

## Overview

**so_long** is a minimalist 2D game written entirely in **C**, built on top of the low-level **MiniLibX** graphics library. The player navigates a tile-based map, collecting every item before reaching the exit — all while the engine validates the world beneath them at load time.

The project emphasizes **clean systems programming**: custom memory management, a two-pass map parser with strict geometric validation, and a lightweight event-driven render loop — no game engine, no shortcuts.

---

## Features

- **Custom Map Parser** — Two-pass parsing pipeline: validates map geometry, counts game entities, and rejects malformed input with descriptive error messages before any memory is allocated for gameplay
- **Strict Validation** — Enforces rectangular boundaries, wall-enclosed perimeter, exactly one player `P`, at least one collectible `C`, exactly one exit `E`, and no invalid symbols
- **XPM Texture Rendering** — Five tile types (`wall`, `floor`, `player`, `collectible`, `exit`), each rendered from `.xpm` sprite files at configurable tile size
- **Event-Driven Input** — Keyboard hooks for WASD + arrow key movement, ESC to quit, and a window close button handler
- **Live Move Counter** — Prints the current move count to stdout on every step
- **Clean Memory Handling** — All heap allocations tracked; `free_map()` and `cleanup_textures()` ensure no leaks on exit or error path

---

## Architecture

```
so_long/
├── so_long.c                  # Entry point — argument validation, parse → allocate → render
├── so_long.h                  # All typedefs, structs, and function prototypes
│
├── check_map_file.c           # parse_map() — full validation pass, error_exit() dispatcher
├── check_lines.c              # Per-line validators: borders, symbols, width consistency
├── allocate_map.c             # allocation_map() — second pass: populates map->grid
├── declaration_structures.c   # Zero-initializers for t_map, t_line; player spawn locator
│
├── render_map.c               # init_game(), render_map() — MiniLibX setup & main loop
├── process_functions.c        # handle_keypress(), processing_moves(), render_grid()
├── textures.c                 # XPM loader and texture cleanup
│
└── libs/
    ├── libft/                 # Custom libc implementation
    ├── libftprintf/           # Custom ft_printf
    └── get_next_line/         # Custom GNL with buffer cleanup
```

---

## Data Flow

```
argv[1]  ──►  parse_map()       validates geometry, counts entities
         ──►  allocation_map()  second open(): populates char** grid
         ──►  render_map()      MiniLibX init, texture load, event loop
                   │
                   ├──  render_grid()        tile-by-tile blit to window
                   ├──  handle_keypress()    movement dispatch + ESC
                   └──  processing_moves()   game logic: collect / exit / walk
```

---

## Map Format

Maps are plain `.ber` text files. Rules enforced at parse time:

| Rule | Requirement |
|------|-------------|
| Shape | Must be a perfect rectangle |
| Borders | Entire perimeter must be `1` (wall) |
| Player `P` | Exactly **1** |
| Exit `E` | Exactly **1** |
| Collectibles `C` | At least **1** |
| Valid symbols | Only `0 1 C E P` allowed |

**Example map:**

```
1111111111
1P0001C001
100011C001
10000000E1
1111111111
```

---

## Structs

```c
typedef struct s_map {
    char  **grid;              // 2D tile array (heap-allocated, row per line)
    int     width, height;
    int     player_count;
    int     exit_count;
    int     collectible_count; // decremented on each pickup; exit unlocks at 0
} t_map;

typedef struct s_player {
    int  x, y;                 // Current tile position
    int  moves;                // Incremented and printed on each valid move
} t_player;

typedef struct s_render {
    int   tile_size;           // Pixels per tile (default: 50)
    void *mlx;
    void *win;
    t_t   t;                   // Five XPM texture handles
} t_render;
```

---

## Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move up |
| `A` / `←` | Move left |
| `S` / `↓` | Move down |
| `D` / `→` | Move right |
| `ESC` | Quit |
| Window `✕` | Quit |

---

## Getting Started

### Prerequisites

- GCC or Clang
- MiniLibX (Linux or macOS)
- X11 development headers (Linux)

### Build

```bash
git clone https://github.com/yourusername/so_long.git
cd so_long
make
```

### Run

```bash
./so_long maps/your_map.ber
```

### Error handling demo

```bash
./so_long maps/no_exit.ber
# Error: Exit count error

./so_long maps/open_border.ber
# Error: Borders are incorrect

./so_long maps/two_players.ber
# Error: Player count error
```

---

## Textures

Place `.xpm` sprites in a `textures/` directory relative to the binary:

```
textures/
├── wall.xpm
├── bg.xpm
├── player.xpm
├── item.xpm
└── exit.xpm
```

All five files must be present and loadable — the engine exits with an error if any texture fails to initialize.

---

## Implementation Notes

**Two-pass parsing** — The map is opened and read twice: once to validate (without allocating the grid), once to populate. This guarantees that `char **grid` is only allocated for a map already known to be valid, keeping error paths clean.

**GNL buffer cleanup** — `free_gnl_buffer()` is called in `error_exit()` to drain any internal GNL state before exit, preventing memory leak reports under Valgrind on early-exit paths.

**Collectible gate** — The exit tile `E` only triggers a win condition when `map->collectible_count == 0`. The count is tracked in `t_map` and decremented at runtime, so no grid rescanning is needed on each move.

**Norminette-compliant** — All functions respect the 42 norm: max 25 lines per function, max 5 variables per scope, no for-loops, strict formatting.

---

## Author

**dkot** — [42 School](https://42.fr)

---

<div align="center">
<sub>Built with C, MiniLibX, and an unreasonable amount of malloc discipline.</sub>
</div>


---

## License

MIT © [denyskotcode](https://github.com/denyskotcode) — see [LICENSE](LICENSE) for details.