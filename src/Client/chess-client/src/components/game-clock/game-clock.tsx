import { Clock } from "../clock/clock";
import styles from "./game-clock.module.css";

export const GameClock: React.FC = () => {
  return (
    <div className={styles.container}>
      <Clock />
      <Clock />
    </div>
  );
};
