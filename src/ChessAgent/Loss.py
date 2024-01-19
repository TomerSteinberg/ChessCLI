def ternary_result_agent_loss(result: str) -> int:
    """
    three result loss functions giving -1 for a win, 0 for a draw and 1 for a loss
    @param: result string (w,d,l)
    @return: loss value
    @rtype: int
    """
    if result == 'd':
        return 0
    return -1 if result == 'w' else 1
