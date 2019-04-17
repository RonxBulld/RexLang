namespace GUI
{
    internal class ProjectManager
    {
        private readonly bool dirty_ = false;

        public bool isDirty()
        {
            return dirty_;
        }

        public bool closeCurrentProject()
        {
            return true;
        }
    }
}