import { Chessboard } from "react-chessboard";
import "./app.css";

function App() {
  return (
    <div className={"container"}>
      <Chessboard
        boardWidth={700}
        boardOrientation={"white"}
        id="board"
        customLightSquareStyle={{ backgroundColor: "#ececd0" }}
        customDarkSquareStyle={{ backgroundColor: "#729551" }}
      ></Chessboard>
      <button>hello</button>
    </div>
  );
}

export default App;
