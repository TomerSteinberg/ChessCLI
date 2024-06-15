import styles from "./app.module.css";
import { Board } from "./components/board/board";
import { GameClock } from "./components/game-clock/game-clock";
import { MoveHistory } from "./components/move-history/move-history";

const App: React.FC = () => {
  return (
    <div className={styles.container}>
      <GameClock />
      <Board />
      <MoveHistory />
    </div>
  );
};

export default App;
