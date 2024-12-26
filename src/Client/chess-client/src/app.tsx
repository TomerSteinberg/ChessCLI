import { useState } from "react";
import styles from "./app.module.css";
import { Board } from "./components/board/board";
import { GameClock } from "./components/game-clock/game-clock";
import { MoveHistory } from "./components/move-history/move-history";
import { useConnectToChessEngine } from "./hooks/ws-connection/connect-to-chess-engine";
import { ConnectionStatus } from "./consts/connection-status";
import CircularProgress from '@mui/material/CircularProgress';


const App: React.FC = () => {
  const [isConnected, setIsConnected] = useState<ConnectionStatus>(ConnectionStatus.DISCONNECTED);
  const socket = useConnectToChessEngine(setIsConnected);
  console.log(isConnected);
  return (
    <div className={styles.container}>
    {
      isConnected === ConnectionStatus.CONNECTED ?
      <div className={styles.gameCard}>
      <GameClock />
      <Board />
      <MoveHistory />
      </div> : 
      <div className={styles.loadingContainer}>
        <CircularProgress />
      <p className={styles.connectionText}>Attempting Connection...</p>
        </div>
    }
      </div>
  );
};

export default App;
