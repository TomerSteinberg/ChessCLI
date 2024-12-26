import React, { SetStateAction, useEffect, useState } from 'react';
import { ConnectionStatus } from '../../consts/connection-status';

const URL = 'ws://localhost:6355';

export const useConnectToChessEngine = (setIsConnected: React.Dispatch<SetStateAction<ConnectionStatus>>) => {
  const [socket, setSocket] = useState<WebSocket | null>(null);

  useEffect(() => {
    console.log("Attempting to connect to WebSocket server...");

    // Establish WebSocket connection
    const socketInstance = new WebSocket(URL);

    socketInstance.onopen = () => {
      console.log("WebSocket connection established");
      setIsConnected(ConnectionStatus.CONNECTED);
    };

    socketInstance.onerror = (error) => {
      console.error("WebSocket error:", error);
      setIsConnected(ConnectionStatus.DISCONNECTED);
    };

    socketInstance.onclose = () => {
      console.log("WebSocket connection closed");
      setIsConnected(ConnectionStatus.CLOSED);
    };

    setSocket(socketInstance);

    // Clean up on component unmount
    return () => {
      console.log("Cleaning up WebSocket connection...");
      socketInstance.close();
    };
  }, [setIsConnected]);

  return socket;
};