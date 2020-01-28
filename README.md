# Corewar

Corewar is a very peculiar game. It’s about bringing “players” together around a “virtual machine”, which will load some “champions” who will fight against one another with the support of “processes”, with the objective being for these champions to stay “alive”.
The processes are executed sequentially within the same virtual machine and memory space. They can therefore, among other things, write and rewrite on top of each others so to corrupt one another, force the others to execute instructions that can damage them.
The game ends when all the processes are dead. The winner is the last player reported to be “alive”.

**This project can be broken down into three distinctive parts:**

- The assembler: this is the program that is compile champions and translate them from the assembly language into “Bytecode”. Bytecode is a machine code, which will be directly interpreted by the virtual machine.
- The virtual machine: It’s the “arena” in which champions (up to 4 at a time) are executed. It offers various functions, all of which are useful for the battle of the champions.
- Visualisation for better understanding about what's happening on the arena.

# Usage

	`make`

	`asm`
	`Usage: ./asm <your_champion.s>`

	`corewar`
	`Usage: ./corewar [-a] [-v] [-l] [-dump <num> -n <num>] <champion.cor> <...>
    -a          : Print output from "aff" (Default is off)
    -dump <num> : Dump memory (32 octets per line) after <num> cycles and exit
    -v          : Run visualizer
    -n    <num> : Set <num> of the next player
    -l          : Print alive when live executed (Default is off)`

You can find champion files in champs folder.

# Who worked on this project:

- assembler [Nygyman](https://github.com/nygymankussainov/)
- virtual machine [Vlad](https://github.com/Sddoo/) and [Arina](https://github.com/egiant)
- visualisation [Vladimir](https://github.com/vlaarx)
