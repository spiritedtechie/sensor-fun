var express = require('express');
var router = express.Router();

router.post('/reading', function(req, res) {
  return res.send({
    "status": "ok"
  });
});

module.exports = router;
