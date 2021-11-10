using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace CarutasuAdrianaS43.Models
{
    public class AppContext: DbContext
    {
        public AppContext() : base("DBConnectionString") 
        {
            Database.SetInitializer(new MigrateDatabaseToLatestVersion<AppContext,
            CarutasuAdrianaS43.Migrations.Configuration>("DBConnectionString"));
        }

        public DbSet<Student> Students { get; set; }
        public DbSet<Domain> Domains { get; set; }
    }
}