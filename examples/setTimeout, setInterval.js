// minimum required CLEO Redux version: 1.0.4

let { setTimeout, setInterval, clearTimeout, clearInterval } = (function () {
  let intervals = [];

  function setTimeout(cb, delay = 0, ...args) {
    let id = intervals.length;
    intervals[id] = true;
    (async () => {
      await asyncWait(delay);
      if (intervals[id]) {
        try {
          cb.apply(undefined, args);
        } catch (e) {
          log(e);
        }
      }
      clearTimeout(id);
    })();
    return id;
  }

  function setInterval(cb, delay = 0, ...args) {
    let id = intervals.length;
    intervals[id] = true;
    (async () => {
      while (true) {
        await asyncWait(delay);
        if (intervals[id]) {
          try {
            cb.apply(undefined, args);
          } catch (e) {
            log(e);
          }
        } else {
          break;
        }
      }
    })();
    return id;
  }

  function clearTimeout(id) {
    intervals[id] = false;
  }

  function clearInterval(id) {
    intervals[id] = false;
  }

  return { setTimeout, setInterval, clearTimeout, clearInterval };
})();
