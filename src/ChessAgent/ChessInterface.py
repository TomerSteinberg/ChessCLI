import sys
import os
import io
import subprocess



def get_options(process):
    """
    Gets a list of possible moves from a position
    @param: process
    @return: list of optional moves
    @rtype: [str] 
    """
    process.stdin.write(b"options;\n")
    process.stdin.flush()

    options = [process.stdout.readline()[-6:-2].decode()]
    while process.stdout.peek().decode() != 'DuckEngine> ':
        options.append(process.stdout.readline()[:4].decode())

    return options


def set_up_process():
    """
    Sets up process
    @param: None
    @return: process
    """
    process = subprocess.Popen("ChessCLIEngine.exe",
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,)

    process.stdout.readline()
    process.stdout.readline()
    process.stdin.write(b"create;\n")
    process.stdin.flush()
    return process


def move(process, move):
    process.stdin.write(f"move {move};\n".encode())
    process.stdin.flush()

    print("here: " + process.stdout.peek().decode())


def get_dump(process):
    pass


process = set_up_process()
move(process, "a2a5")
move(process, "e2e4")
move(process, "a7a5")


process.kill()