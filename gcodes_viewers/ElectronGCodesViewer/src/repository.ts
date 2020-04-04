export class Repository {
    private m_gcodesFilePath: string;
  
    public gcodesFilePath() {
      return this.m_gcodesFilePath;
    }
  
    public setGCodesFilePath(value: string)
    {
      this.m_gcodesFilePath = value;
    }
}