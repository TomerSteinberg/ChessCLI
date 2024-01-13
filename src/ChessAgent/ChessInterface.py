import subprocess


def options(process):
    """
    Gets a list of possible moves from a position
    @param: process
    @return: list of optional moves
    @rtype: [str] 
    """
    process.stdin.write(b"options\n")
    process.stdin.flush()

    options = [process.stdout.readline()[-6:-2].decode()]
    while process.stdout.peek().decode() != 'DuckEngine> ':
        options.append(process.stdout.readline()[:4].decode())
    return options


def create_interface():
    """
    Sets up process
    @param: None
    @return: process
    @rtype: Popen
    """
    process = subprocess.Popen("ChessCLIEngine.exe",
                               bufsize=1024,
                               stdin=subprocess.PIPE,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,)
    process.stdout.readline()
    process.stdout.readline()
    process.stdin.write(b"create\n")
    
    return process


def move(process, move):
    """
    Interface for playing a move
    @param: Process and move to play 
    @return: status
    @rtype: bool
    """
    process.stdin.write(f"move {move}\n".encode())
    process.stdin.flush()

    valid = b':' not in process.stdout.read(len(process.stdout.peek()))
    if process.stdout.peek() != b'DuckEngine> ':
        valid = b':' not in process.stdout.read(len(process.stdout.peek()))
    return valid


def dump(process, flag=''):
    """
    Interface for dump command
    @param: Process and dump flags (-b -h -l)
    @return: board dump items
    @rtype: [str]
    """
    process.stdin.write(f"dump {flag}\n".encode())
    process.stdin.flush()

    board_dump = [process.stdout.readline().decode().split("DuckEngine> ")[-1][:-2]]
    while process.stdout.peek().decode() != 'DuckEngine> ':
        board_dump.append(process.stdout.readline().decode()[:-2])
    return board_dump


def back(process):
    """
    Interface for back command
    @param: Process
    @return: None
    """
    process.stdin.write(b"back\n")
    process.stdin.flush()


def truncate(process):
    """
    Interface for truncate command
    @param: Process
    @return: None
    """
    process.stdin.write(b"truncate\n")
    process.stdin.flush()
