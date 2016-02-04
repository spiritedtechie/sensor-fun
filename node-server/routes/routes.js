var appRouter = function(app) {
  app.post("/reading", function(req, res) {
    return res.send({"status": "ok"});
  });
}

module.exports = appRouter;
