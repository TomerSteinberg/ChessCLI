import { Chessboard } from "react-chessboard";
import styles from "./board.module.css";

export const Board: React.FC = () => {
  return (
    <div className={styles.boardContainer}>
      <Chessboard
        boardWidth={700}
        showBoardNotation
        boardOrientation={"white"}
        id="board"
        customLightSquareStyle={{ backgroundColor: "#ececd0" }}
        customDarkSquareStyle={{ backgroundColor: "#729551" }}
      ></Chessboard>
    </div>
  );
};
