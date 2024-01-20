from ChessInterface import options, move, back, truncate, create_interface, dump, history
import tensorflow as tf
import numpy as np
from tensorflow import keras


def process_dump(dump_bitboards):
    """
    Processes dump bitboards
    @Param: list of bitboards
    @Returns: stacked bitboard tensor
    """
    dump_bitboards[-1] = "".join(['0' for i in range(56)]) + dump_bitboards[-1]
    dump_bitboards[-2] = "".join(['0' for i in range(56)]) + dump_bitboards[-2]
    dump_num = list(map(lambda d: list([(1 - int(i)) for i in d ]), dump_bitboards))

    bitboard_input = tf.one_hot(dump_num[0], 1,dtype=tf.int64, axis=0)
    bitboard_input = [tf.reshape(bitboard_input, (8,8))]
    for bitboard in dump_num[1:]:
        dump_tensor = tf.one_hot(bitboard, 1,dtype=tf.int64, axis=0)
        dump_tensor = tf.reshape(dump_tensor, (8,8))
        bitboard_input.append(dump_tensor)
    

    bitboard_input = tf.stack(bitboard_input, axis=-1)
    return bitboard_input


def value_action(actions, model, game_interface):
    """
    Creates a value action pair based on best move prediction
    @Param: list of possible actions, model and game interface
    @Returns: best value action pair
    """
    best_action = 'over'
    best_value = -100
    illegal_streak = 0

    for action in actions:
        if move(game_interface, action):
            bitboards = dump(game_interface, '-b')
            value = model(tf.expand_dims(process_dump(bitboards), axis=0), training=True)
            #print("Value: " + str(value[0][0]) + " Move:" + action)
            if value > best_value:
                best_value = value
                best_action = action
            back(game_interface)
            truncate(game_interface)
        else:
            illegal_streak += 1
            if illegal_streak == len(actions):
                return (-100, 'over')
    #print('Best value: ' + str(best_value[0][0]), end='\t')
    #print('Best move: ' + best_action)
    return (best_value, best_action)
    

def sample_game(model, color):
    """
    Plays a game of chess and returns result
    @param: model and color of player
    @return: result
    """
    game_interface = create_interface()
    action = ''
    moves_made = 0

    while action != 'over':
        if moves_made == 5:
            return 0.5
        moves = options(game_interface)
        value, action = value_action(moves, model, game_interface)
        if action == 'over':
            break
        move(game_interface, action)
        moves_made += 1
        if moves_made % 20 == 0:
            print(history(game_interface))


    print(history(game_interface))
    game_interface.kill()

    if (moves_made % 2 == 1 and color == 'w') or (moves_made % 2 == 0 and color == 'b'):
        return 0
    else:
        return 1


def train_step(model, color):
    """
    Computes a single training step
    @param: model and color of player
    @returns: None
    """
    with tf.GradientTape() as tape:
        loss = model.loss([0], [sample_game(model, color)])
    gradients = tape.gradient(loss, model.variables)
    print(gradients)
    model.optimizer.apply_gradients(zip(gradients, model.variables))


def train_loop(model, epoch=1):
    """
    Computes a full training loop
    @param: model, number of epochs (games)
    @return: None
    """
    color = 'w'
    for i in range(epoch):
        train_step(model, color)
        if color == 'w':
            color = 'b'
        else:
            color = 'w'
            
    model.save()

