// Fxt Loader (FxtLoader.cleo, FxtLoader64.cleo)
declare module "*.fxt" {
  const value: Record<string, string>;
  export default value;
}
