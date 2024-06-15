import styles from "./clock.module.css";

export const Clock: React.FC = () => {
  return (
    <div className={styles.container}>
      <p className={styles.time}>10:00</p>
    </div>
  );
};
