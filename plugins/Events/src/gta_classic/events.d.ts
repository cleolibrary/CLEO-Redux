declare function addEventListener(
  event: "OnVehicleCreate",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;

declare function addEventListener(
  event: "OnPedCreate",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;

declare function addEventListener(
  event: "OnObjectCreate",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;

declare function addEventListener(
  event: "OnVehicleDelete",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;

declare function addEventListener(
  event: "OnPedDelete",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;

declare function addEventListener(
  event: "OnObjectDelete",
  callback: (event: CleoEvent<{ address: number }>) => void
): () => void;
