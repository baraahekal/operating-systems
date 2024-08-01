import React, { useState } from 'react';
import {
    Button, TextField, FormControl, FormLabel, RadioGroup, FormControlLabel, Radio, Select, MenuItem, Switch, Grid, Card, CardContent, Typography, CardActions
} from '@mui/material';

const SchedulerConfiguration = ({ onSubmit }) => {
    const [algorithm, setAlgorithm] = useState('fcfs');
    const [direction, setDirection] = useState('right');
    const [cylinders, setCylinders] = useState(200);
    const [requests, setRequests] = useState('');
    const [startingHead, setStartingHead] = useState('');

    const handleSubmit = (event) => {
        event.preventDefault();
        onSubmit({
            algorithm,
            direction,
            cylinders,
            starting_head: Number(startingHead),
            requests: requests.split(',').map(Number)
        });
    };

    return (
        <Card sx={{ margin: '20px', backgroundColor: 'background.paper' }}>
            <CardContent>
                <Typography variant="h5" component="h2">
                    Scheduler Configuration
                </Typography>
                <form onSubmit={handleSubmit} style={{ marginTop: '20px' }}>
                    <Grid container spacing={3}>
                        <Grid item xs={12}>
                            <FormControl fullWidth>
                                <FormLabel>Algorithm</FormLabel>
                                <Select value={algorithm} onChange={(e) => setAlgorithm(e.target.value)}>
                                    <MenuItem value="fcfs">FCFS</MenuItem>
                                    <MenuItem value="sstf">SSTF</MenuItem>
                                    <MenuItem value="scan">SCAN</MenuItem>
                                    <MenuItem value="look">LOOK</MenuItem>
                                    <MenuItem value="c_scan">C-SCAN</MenuItem>
                                    <MenuItem value="c_look">C-LOOK</MenuItem>
                                </Select>
                            </FormControl>
                        </Grid>
                        <Grid item xs={12}>
                            <FormControl component="fieldset">
                                <FormLabel>Head Direction</FormLabel>
                                <RadioGroup row value={direction} onChange={(e) => setDirection(e.target.value)}>
                                    <FormControlLabel value="left" control={<Radio />} label="Left" />
                                    <FormControlLabel value="right" control={<Radio />} label="Right" />
                                </RadioGroup>
                            </FormControl>
                        </Grid>

                        <Grid item xs={12}>
                            <TextField
                                label="Cylinders"
                                type="number"
                                value={cylinders}
                                onChange={(e) => setCylinders(Number(e.target.value))}
                                fullWidth
                            />
                        </Grid>
                        <Grid item xs={12}>
                            <TextField
                                label="Starting Head"
                                type="number"
                                value={startingHead}
                                onChange={(e) => setStartingHead(Number(e.target.value))}
                                fullWidth
                            />
                        </Grid>
                        <Grid item xs={12}>
                            <TextField
                                label="Disk Requests"
                                value={requests}
                                onChange={(e) => setRequests(e.target.value)}
                                fullWidth
                            />
                        </Grid>
                    </Grid>
                    <CardActions sx={{ marginTop: '20px' }}>
                        <Button type="submit" variant="contained" color="primary" fullWidth>
                            Confirm Configuration
                        </Button>
                    </CardActions>
                </form>
            </CardContent>
        </Card>
    );
};

export default SchedulerConfiguration;
