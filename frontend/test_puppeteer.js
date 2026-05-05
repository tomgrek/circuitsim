const puppeteer = require('puppeteer');

(async () => {
  const browser = await puppeteer.launch({ args: ['--no-sandbox'] });
  const page = await browser.newPage();
  
  page.on('console', msg => {
    console.log(`BROWSER CONSOLE: ${msg.text()}`);
  });
  
  await page.goto('http://localhost:5173');
  
  // Wait for React to mount and render the Simulate button
  await page.waitForSelector('button');
  
  // Find the Simulate button
  const buttons = await page.$$('button');
  for (const btn of buttons) {
    const text = await page.evaluate(el => el.textContent, btn);
    if (text.includes('Simulate')) {
      console.log("Clicking Simulate...");
      await btn.click();
      break;
    }
  }
  
  // Wait a few seconds for simulation to finish and logs to appear
  await new Promise(r => setTimeout(r, 3000));
  
  await browser.close();
})();
